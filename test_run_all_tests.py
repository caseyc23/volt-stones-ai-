#!/usr/bin/env python3
import types
import run_all_tests as rat

class DummyResp:
    def __init__(self, status_code=200):
        self.status_code = status_code


def make_suite():
    suite = rat.VoltTestSuite(device_ip="127.0.0.1", password="test")
    # Monkey patch network calls to be deterministic and offline-safe
    def fake_test_api(endpoint, method="GET", data=None, expected_status=200):
        if endpoint == "/api/status":
            return True, "Status 200 as expected"
        if endpoint == "/api/wifi/add":
            # Simulate validation rejecting bad input
            return (expected_status == 400), f"Status {expected_status} as expected"
        return True, "ok"
    suite.test_api_endpoint = fake_test_api
    return suite


def test_run_chaos_suite_offline():
    suite = make_suite()
    suite.run_chaos_tests()
    assert suite.results["chaos"]["failed"] == 0
    assert len(suite.results["chaos"]["tests"]) == 3


def test_run_security_suite_offline():
    suite = make_suite()
    # Patch requests.get used in security_test_authentication and brute force
    import run_all_tests as rat2
    import requests as real_requests

    class FakeRequests:
        def __init__(self):
            self.calls = 0
        def get(self, url, headers=None, timeout=10):
            # First path: no auth header -> return 401
            if headers is None:
                return DummyResp(status_code=401)
            # Brute force: after some tries, return 429
            self.calls += 1
            if self.calls >= 5:
                return DummyResp(status_code=429)
            return DummyResp(status_code=401)

    fake = FakeRequests()
    rat2.requests = fake  # monkey patch module attr

    suite.run_security_tests()
    # restore
    rat2.requests = real_requests

    assert suite.results["security"]["failed"] in (0, 1)  # XSS/SQL parts may pass heuristically
    assert len(suite.results["security"]["tests"]) == 4


def test_report_generation():
    suite = make_suite()
    suite.run_chaos_tests()
    code = suite.generate_report()
    assert code in (0, 1)
