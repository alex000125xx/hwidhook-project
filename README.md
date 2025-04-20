@echo off
REM — MachineGuid من الريجستري
for /f "tokens=3" %%A in ('reg query "HKLM\SOFTWARE\Microsoft\Cryptography" /v MachineGuid 2^>nul') do echo %%A

REM — رقم تسلسل القرص C:
for /f "tokens=5" %%A in ('vol C: 2^>nul') do echo %%A

REM — System UUID
for /f "skip=1 tokens=*" %%A in ('wmic csproduct get UUID 2^>nul') do if not "%%A"=="" echo %%A

REM — BIOS SerialNumber
for /f "skip=1 tokens=*" %%A in ('wmic bios get SerialNumber 2^>nul') do if not "%%A"=="" echo %%A

REM — Baseboard SerialNumber
for /f "skip=1 tokens=*" %%A in ('wmic baseboard get SerialNumber 2^>nul') do if not "%%A"=="" echo %%A

REM — CPU ProcessorId
for /f "skip=1 tokens=*" %%A in ('wmic cpu get ProcessorId 2^>nul') do if not "%%A"=="" echo %%A

REM — DiskDrive SerialNumber
for /f "skip=1 tokens=*" %%A in ('wmic diskdrive get SerialNumber 2^>nul') do if not "%%A"=="" echo %%A
