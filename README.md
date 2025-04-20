@echo off
title عرض كافة معرفات الجهاز (HWID وبيانات النظام)
echo.
echo ========================== المعلومات العامة ==========================
echo Computer Name:
echo -------------
echo %COMPUTERNAME%
echo.

echo ========================= MachineGuid (Registry) =========================
echo reg query "HKLM\SOFTWARE\Microsoft\Cryptography" /v MachineGuid
reg query "HKLM\SOFTWARE\Microsoft\Cryptography" /v MachineGuid 2>nul
echo.

echo ======================== Volume Serial Number (C:) ========================
echo vol C:
vol C:
echo.

echo ========================= System UUID (WMIC) =========================
for /f "skip=1 tokens=*" %%A in ('wmic csproduct get UUID') do (
  if not "%%A"=="" echo UUID: %%A
)
echo.

echo ======================== BIOS Serial Number (WMIC) ========================
for /f "skip=1 tokens=*" %%A in ('wmic bios get SerialNumber') do (
  if not "%%A"=="" echo BIOS SerialNumber: %%A
)
echo.

echo =================== Baseboard (Motherboard) Serial (WMIC) ==================
for /f "skip=1 tokens=*" %%A in ('wmic baseboard get SerialNumber') do (
  if not "%%A"=="" echo Baseboard SerialNumber: %%A
)
echo.

echo ======================= CPU Processor ID (WMIC) =======================
for /f "skip=1 tokens=*" %%A in ('wmic cpu get ProcessorId') do (
  if not "%%A"=="" echo ProcessorId: %%A
)
echo.

echo ==================== DiskDrive Serial Numbers (WMIC) ===================
for /f "skip=1 tokens=*" %%A in ('wmic diskdrive get SerialNumber') do (
  if not "%%A"=="" echo DiskDrive SerialNumber: %%A
)
echo.

echo ============================= الانتهاء =============================
pause
