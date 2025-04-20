reg query "HKLM\SOFTWARE\Microsoft\Cryptography" /v MachineGuid
vol C:
wmic csproduct get UUID
wmic bios get SerialNumber
wmic baseboard get SerialNumber
wmic cpu get ProcessorId
wmic diskdrive get SerialNumber
