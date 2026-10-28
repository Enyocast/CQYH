<#
.SYNOPSIS
  Overlays the prebuilt "Win32 - Modified and Compiled" map editor onto client\UE3\Binaries\Win32.

.PARAMETER BundleDir
  The extracted "Win32 - Modified and Compiled" folder (from the release's "Map Editor Tool Description").

.PARAMETER ShaderWorker
  Optional: a genuine UE3ShaderCompileWorker.exe (the 56 KB 2015 one). The 274 KB 2020 file that ships with
  Client Assets is not the same program and does not work.

Only .exe / .dll / .config files are copied (not the .pdb/.ilk/.lib/.exp/.response/.dmp build leftovers). Every file it
replaces is first copied to client\UE3\Binaries\Win32\_backup_prebuilt_overlay. Nothing in git is changed: these are
build outputs, ignored by .gitignore.
#>
param(
    [Parameter(Mandatory)] [string] $BundleDir,
    [string] $ShaderWorker
)
$ErrorActionPreference = 'Stop'
$bin = Join-Path $PSScriptRoot 'client\UE3\Binaries\Win32'
if (-not (Test-Path -LiteralPath $bin))       { throw "Not found: $bin (is Client Assets in place?)" }
if (-not (Test-Path -LiteralPath $BundleDir)) { throw "Not found: $BundleDir" }

$backup = Join-Path $bin '_backup_prebuilt_overlay'
New-Item -ItemType Directory -Force $backup | Out-Null

$copied = 0
Get-ChildItem -LiteralPath $BundleDir -File | Where-Object { $_.Extension -in '.exe', '.dll', '.config' } | ForEach-Object {
    $dest = Join-Path $bin $_.Name
    if (Test-Path -LiteralPath $dest) { Copy-Item -LiteralPath $dest -Destination $backup -Force }
    Copy-Item -LiteralPath $_.FullName -Destination $dest -Force
    $copied++
}
Write-Host "Overlaid $copied files into $bin (replaced files backed up to $backup)"

if ($ShaderWorker) {
    $dest = Join-Path $bin 'UE3ShaderCompileWorker.exe'
    if (Test-Path -LiteralPath $dest) { Copy-Item -LiteralPath $dest -Destination $backup -Force }
    Copy-Item -LiteralPath $ShaderWorker -Destination $dest -Force
    Write-Host "Installed shader compile worker ($((Get-Item $dest).Length) bytes)"
}

if (-not (Test-Path -LiteralPath (Join-Path $bin 'MMOGame.exe'))) { Write-Warning 'MMOGame.exe is still missing in Binaries\Win32.' }
Write-Host 'Next: set SourceControl Disabled=True / AutoAddNewFiles=False in MMOGame\Config\DefaultEditorUserSettings.ini and MMOEditorUserSettings.ini, then run Launch_Editor_DX9.bat'