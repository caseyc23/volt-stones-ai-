# VOLT v5.00 - Complete Backup Script
# Creates a ZIP archive of all VOLT files

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "VOLT v5.00 - Complete Backup Creator" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$sourceDir = Get-Location
$desktopPath = [Environment]::GetFolderPath("Desktop")
$timestamp = Get-Date -Format "yyyy-MM-dd_HH-mm-ss"
$zipFileName = "VOLT_v5.00_Professional_$timestamp.zip"
$zipPath = Join-Path $desktopPath $zipFileName

Write-Host "Source: $sourceDir" -ForegroundColor Yellow
Write-Host "Destination: $zipPath" -ForegroundColor Yellow
Write-Host ""

$tempDir = Join-Path $env:TEMP "VOLT_Backup_$timestamp"
New-Item -ItemType Directory -Path $tempDir -Force | Out-Null

Write-Host "Copying files..." -ForegroundColor Cyan

# Core files
$coreFiles = @("ota_update.h", "power_management.h", "watchdog.h", "library.json", "config.template.h")
Write-Host "  - Core firmware files (5)" -ForegroundColor White
foreach ($file in $coreFiles) {
    if (Test-Path $file) { Copy-Item $file -Destination $tempDir -Force }
}

# Documentation
$docFiles = @("README.md", "HOW_TO_FLASH.md", "VOICE_OPTIONS.md", "HARDWARE_TESTING_CHECKLIST.md", 
              "VOLT_CONNECTION_TROUBLESHOOTING.md", "FIX_VOLT_CONNECTION.md", "COMPREHENSIVE_TESTING_SUITE.md",
              "COMPREHENSIVE_TESTING_SUITE_FIXED.md", "FILE_INSPECTION_REPORT.md", 
              "FIRMWARE_TESTING_AND_COMPARISON_GUIDE.md", "PROFESSIONAL_UPGRADE_COMPLETE.md",
              "QUICK_START_PROFESSIONAL.md", "FINAL_SUMMARY.md", "TESTING_EXECUTION_GUIDE.md",
              "COMPLETE_FLASHING_PLATFORM_GUIDE.md", "DISTRIBUTION_README.md")
Write-Host "  - Documentation files (16)" -ForegroundColor White
foreach ($file in $docFiles) {
    if (Test-Path $file) { Copy-Item $file -Destination $tempDir -Force }
}

# Tools
$toolFiles = @("run_all_tests.py", "setup_wizard.py", "configurator.html")
Write-Host "  - Tool files (3)" -ForegroundColor White
foreach ($file in $toolFiles) {
    if (Test-Path $file) { Copy-Item $file -Destination $tempDir -Force }
}

# Examples
if (Test-Path "examples") {
    Write-Host "  - Examples directory (5 examples)" -ForegroundColor White
    Copy-Item "examples" -Destination $tempDir -Recurse -Force
}

Write-Host ""
Write-Host "Creating ZIP archive..." -ForegroundColor Cyan

try {
    Compress-Archive -Path "$tempDir\*" -DestinationPath $zipPath -Force
    
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "SUCCESS! Backup created!" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Location: $zipPath" -ForegroundColor Yellow
    Write-Host "Size: $([math]::Round((Get-Item $zipPath).Length / 1MB, 2)) MB" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "The ZIP file is on your Desktop!" -ForegroundColor Green
    Write-Host ""
    
    Remove-Item $tempDir -Recurse -Force
    Start-Process "explorer.exe" -ArgumentList $desktopPath
    
} catch {
    Write-Host ""
    Write-Host "ERROR: $($_.Exception.Message)" -ForegroundColor Red
}

Write-Host "Press any key to exit..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
