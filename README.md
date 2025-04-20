@echo off
REM MachineGuid
for /f "tokens=3" %%A in ('reg query "HKLM\SOFTWARE\Microsoft\Cryptography" /v MachineGuid') do echo %%A

REM Volume Serial (C:)
for /f "skip=1 tokens=5" %%A in ('vol C:') do echo %%A

REM System UUID
for /f "skip=1 tokens=*" %%A in ('wmic csproduct get UUID') do if not "%%A"=="" echo %%A

REM BIOS Serial Number
for /f "skip=1 tokens=*" %%A in ('wmic bios get SerialNumber') do if not "%%A"=="" echo %%A

REM Baseboard Serial Number
for /f "skip=1 tokens=*" %%A in ('wmic baseboard get SerialNumber') do if not "%%A"=="" echo %%A

REM CPU ProcessorId
for /f "skip=1 tokens=*" %%A in ('wmic cpu get ProcessorId') do if not "%%A"=="" echo %%A

REM DiskDrive Serial Number
for /f "skip=1 tokens=*" %%A in ('wmic diskdrive get SerialNumber') do if not "%%A"=="" echo %%A
