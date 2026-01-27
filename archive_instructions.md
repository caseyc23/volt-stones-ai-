# Archive duplicates — Safe commands to run locally

I attempted to archive duplicates automatically but the execution environment couldn't move all files reliably. Below are safe, copy-and-paste PowerShell commands you can run on your Windows machine to move the duplicate documentation and legacy firmware copies into a workspace archive folder.

Run these steps from PowerShell (as your normal user):

1. Create an archive folder inside the workspace:

```powershell
mkdir "C:\Users\Holle\Desktop\volt v5.00 flash\archive"
```

2. Back up original OneDrive firmware copies (optional but recommended):

```powershell
# Copy the OneDrive project bundles into archive (do not delete originals)
Copy-Item -LiteralPath "C:\Users\Holle\OneDrive\Desktop\VOLT_v5.00_Professional_2026-01-24_23-52-08" -Destination "C:\Users\Holle\Desktop\volt v5.00 flash\archive\VOLT_v5.00_Professional_2026-01-24_23-52-08" -Recurse -Force
Copy-Item -LiteralPath "C:\Users\Holle\OneDrive\Desktop\volt-stones-ai--main" -Destination "C:\Users\Holle\Desktop\volt v5.00 flash\archive\volt-stones-ai--main" -Recurse -Force
Copy-Item -LiteralPath "C:\Users\Holle\OneDrive\v1_firmware" -Destination "C:\Users\Holle\Desktop\volt v5.00 flash\archive\v1_firmware" -Recurse -Force
```

3. Move workspace documentation, scripts and duplicate headers into the archive (Tidy root, keep only `firmware_final/`):

```powershell
$root = "C:\Users\Holle\Desktop\volt v5.00 flash"
$archive = Join-Path $root 'archive'
# Move markdown docs (keep README.md but archive everything else)
Get-ChildItem -Path $root -Filter *.md -File | Where-Object { $_.Name -ne 'README.md' } | Move-Item -Destination $archive -Force
# Move top-level scripts and headers
Move-Item -Path "$root\*.ps1" -Destination $archive -Force -ErrorAction SilentlyContinue
Move-Item -Path "$root\*.py" -Destination $archive -Force -ErrorAction SilentlyContinue
Move-Item -Path "$root\*.h" -Destination $archive -Force -ErrorAction SilentlyContinue
Move-Item -Path "$root\*.json" -Destination $archive -Force -ErrorAction SilentlyContinue
Move-Item -Path "$root\*.html" -Destination $archive -Force -ErrorAction SilentlyContinue
```

4. Move large legacy folders (if present under the workspace root):

```powershell
Move-Item -LiteralPath "$root\restored_code" -Destination $archive -Force -ErrorAction SilentlyContinue
Move-Item -LiteralPath "$root\volt-stones-ai--main" -Destination $archive -Force -ErrorAction SilentlyContinue
Move-Item -LiteralPath "$root\VOLT_v5.00_Professional_2026-01-24_23-52-08" -Destination $archive -Force -ErrorAction SilentlyContinue
```

5. Confirm the archive contents:

```powershell
Get-ChildItem "$archive" | Sort-Object Name | Format-Table Name,Mode,Length -AutoSize
```

Notes & safety

- These commands MOVE files from the workspace root into the `archive/` folder inside the workspace. The originals in OneDrive (outside the workspace) are LEFT AS IS.
- If you want to COPY instead of MOVE, use `Copy-Item -Recurse -Force` instead of `Move-Item` for the commands above.
- If you prefer I perform the moves for you from here, say so; I attempted automatic moves but the environment had some path errors when acting on your OneDrive folders — I can retry specific moves if you confirm you want them moved.

After you run these commands, your workspace root will be much cleaner and `firmware_final/` will be the canonical build folder for flashing to the HU-087 watch.

---

If you want, I can now:

- Create a consolidated `firmware_final/README.md` with the exact Flash & Test checklist.
- Add a small `ARCHIVE_LOG.md` listing moved items (I can do this automatically after you run the moves),
- Or attempt to complete the archive moves from here if you confirm permission to modify OneDrive files.

Tell me which you'd prefer.
