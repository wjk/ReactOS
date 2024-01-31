/*
 * PROJECT:     ReactOS 'Layers' Shim library
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     VBoxDesktopClassInstaller shim
 * COPYRIGHT:   Copyright 2024 William Kent
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <setupapi.h>
#include <tchar.h>
#include <strsafe.h>
#include <debug.h>
#include <shimlib.h>

typedef DWORD (WINAPI * DISPLAYCLASSINSTALLERPROC)(DI_FUNCTION function, HDEVINFO deviceInfo, PSP_DEVINFO_DATA deviceDetail);

#define SHIM_NS         VirtualBoxClassInstaller
#include <setup_shim.inl>

DWORD WINAPI
SHIM_OBJ_NAME(DisplayClassInstaller)(IN DI_FUNCTION InstallFunction,
                                     IN HDEVINFO DeviceInfoSet,
                                     IN PSP_DEVINFO_DATA DeviceInfoData OPTIONAL)
{
    DWORD rc = CALL_SHIM(0, DISPLAYCLASSINSTALLERPROC)(InstallFunction, DeviceInfoSet, DeviceInfoData);

    if (rc == ERROR_SUCCESS)
    {
        HINF hInf;
        INFCONTEXT ContextManufacturer;
        TCHAR ManufacturerSection[LINE_LEN + 1];
        TCHAR SectionNameMod[MAX_PATH];
        SP_DEVINSTALL_PARAMS InstallParams = {0};
        SP_DRVINFO_DETAIL_DATA DriverInfoDetailData = {0};
        SP_DRVINFO_DATA DriverInfoData = {0};
        HKEY hDeviceSubKey = NULL;
        BOOL result;

        InstallParams.cbSize = sizeof(InstallParams);
        result = SetupDiGetDeviceInstallParams(DeviceInfoSet, DeviceInfoData, &InstallParams);
        if (!result) {
            rc = GetLastError();
            DPRINT("SetupDiGetSelectedDriver() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

        DriverInfoData.cbSize = sizeof(DriverInfoData);
        result = SetupDiGetSelectedDriver(DeviceInfoSet, DeviceInfoData, &DriverInfoData);
        if (!result) {
            rc = GetLastError();
            DPRINT("SetupDiGetDriverInfoDetail() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

        DriverInfoDetailData.cbSize = sizeof(DriverInfoDetailData);
        result = SetupDiGetDriverInfoDetail(DeviceInfoSet, DeviceInfoData,
                                            &DriverInfoData, &DriverInfoDetailData,
                                            sizeof(DriverInfoDetailData), NULL);


        if (!result) {
            rc = GetLastError();
            DPRINT("SetupDiGetDriverInfoDetail() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

        hInf = SetupOpenInfFile(DriverInfoDetailData.InfFileName, NULL, INF_STYLE_WIN4, NULL);
        if (hInf == INVALID_HANDLE_VALUE)
        {
            rc = GetLastError();
            DPRINT("SetupOpenInfFile() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

        result = SetupFindFirstLine(hInf, _T("Manufacturer"), NULL, &ContextManufacturer);
        if (!result)
        {
            rc = GetLastError();
            DPRINT("SetupFindFirstLine() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

        result = SetupGetStringField(
            &ContextManufacturer, 1, /* Field index */
            ManufacturerSection, LINE_LEN, NULL);
        if (!result)
        {
            rc = GetLastError();
            DPRINT("SetupGetStringField() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

        StringCbCopy(SectionNameMod, sizeof(SectionNameMod), ManufacturerSection);
        StringCbCat(SectionNameMod, sizeof(SectionNameMod), _T(".SoftwareSettings"));
        result = SetupInstallFromInfSection(
            InstallParams.hwndParent, hInf, SectionNameMod, SPINST_REGISTRY, hDeviceSubKey, NULL, 0, NULL, NULL,
            NULL,
            NULL);
        if (!result)
        {
            rc = GetLastError();
            DPRINT("SetupInstallFromInfSection() failed with error 0x%lx\n", rc);
            goto cleanup;
        }

    cleanup:
        if (hInf != INVALID_HANDLE_VALUE)
            SetupCloseInfFile(hInf);

        if (hDeviceSubKey != NULL)
            RegCloseKey(hDeviceSubKey);
    }

    return rc;
}

#define SHIM_NUM_HOOKS 1
#define SHIM_SETUP_HOOKS \
    SHIM_HOOK(0, "desk.cpl", "DisplayClassInstaller", SHIM_OBJ_NAME(DisplayClassInstaller))

#include <implement_shim.inl>
