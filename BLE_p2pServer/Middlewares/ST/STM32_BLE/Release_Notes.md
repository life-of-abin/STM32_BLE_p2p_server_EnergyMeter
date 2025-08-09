---
pagetitle: Release Notes for STM32_BLE Middleware
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="../../../_htmresc/favicon.png"/>
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for 
# <mark>STM32_BLE Middleware</mark>
Copyright &copy; 2024 STMicroelectronics\
    
[![ST logo](../../../_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# Purpose

STM32_BLE Middleware for ST Bluetooth LE stack v4.x.

The following Bluetooth LE specification v5.4 features are supported:

-   Advertising
-   Scanning
-   Central / Peripheral Connection
-   GATT Client / Server
-   Host and Controller Privacy
-   LE Encryption
-   Direction Findings (AoA, AoD)
-   LE Data Packet Length Extension
-   LE Legacy and Secure Connections
-   2Mbit PHY
-   LE Long Range (Coded PHY)
-   High Duty Cycle Non-Connectable Advertising
-   Extended advertising and scanning
-   LE Channel Selection Algorithm #2
-   GATT Robust Caching
-   Periodic Advertising and Periodic Advertising Sync Transfer
-   Periodic Advertising with Responses
-   Advertising Coding selection
-   Encrypted Advertising Data
-   LE Ping procedure
-   LE L2CAP Connection-Oriented Channel support
-   LE Power Control & Path Loss Monitoring support
-   Connection robustness mechanism
-   LE channel classification
-   Enhanced ATT (EATT) support
-   Connection subrating support
-   Broadcast Isochronous Streams (BIS) support
-   Connection Isochronous Streams (CIS) support
-   Multiple/concurrent active links supported (tested up to 24)
-   Direct Test Mode
-   Link statistics
-   ATT Maximum Transmission Unit (MTU) size is 1020 octets.
-   L2CAP Maximum Payload Size (MPS) size is 1024 octets.
-   MISRA-C:2012 compliance
-   Bluetooth LE stack modular configurations allowing to optimize
    Bluetooth LE stack memory footprints based on user application
    scenario
-   Single Bluetooth LE stack v4.x binary image (stm32wb0x_ble_stack.a)
    which can be used for all the supported toolchains
-   Dedicated Bluetooth LE stack v4.x binary image (stm32wb0x_ble_stack_controller_only.a) for the HCI controller only configuration

The list of Bluetooth LE commands is documented in the
STM32WB0_BLE_Wireless_Interface document on STM32_BLE\\stack\\doc
folder.
:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section130" checked aria-hidden="true">
<label for="collapse-section130" aria-hidden="true">__V1.3.0 / 04-June-2025__</label>
<div>
<div>
## Main Changes

ST Bluetooth LE stack v4.0d release:

-   New features/updates (compared to Bluetooth LE stack v4.0c):
    -   ID 1333960: Added new API (BLE_STACK_TickNoEvents()) to be used from interrupt context.
    
-   Solved issues (compared to Bluetooth LE stack v4.0c):
    -   ID 1397260: Connection from PAwR cannot be stablished when privacy is used.
    -   ID 1164880: Some requirements for the Access Address generation are not implemented.
    -   ID 1357406: Multiple ACL connections allowed with same peer devices when privacy is used.
    -   ID 1358692: CIS creation is not performed if LE Power Control procedures are ongoing.
    -   ID 1382562: Fixed unexpected disconnections of ISO and ACL links.
    -   ID 1400292: Issue with code modularity feature and Data Length Extension.
    -   ID 1412508: Wrong SCA reported in LL_PERIODIC_SYNC_IND PDU.
    -   ID 1414710: Wrong ACL DATA reported to the Host when CTE header is present.
    -   ID 1417967: PADV wrong timings on Broadcaster for Coded PHY.
    -   ID 1419420: Timing accuracy of 50 ppm not respected when sending AUX_SYNC_SUBEVENT_RSP on a response slot with an high index.
    -   ID 1419451: Request to create a connection from PAwR fails if there are pending data for the specified subevent.
    -   ID 1420542: Unresponsive synchronizer device after PAST procedure failure.
    -   ID 1426217: Null pointer dereferencing when using CIS.    

-   Known limitations:
    -   ID 600131: Erasing the SDB through the aci_gap_clear_security_db command shall be avoided during intense radio activities.
    -   ID 974202: Wrong data reported when ExtendedHeaderLength are less than the correct value.
    -   ID 1074817: Different advertising filter policies are allowed among different adverting sets. It should be forbidden according to GAP specifications.
    -   ID 1166170: Not possible to specify Mode 1 Level 4 requirements for a GATT characteristic.
    -   ID 1197644: Non-optimal pre-scheduler allocation under 10 ms of connection interval.
    -   ID 1213293: The Advertiser_Address shall be checked in according to Advertiser_Address_Type value for some HCI commands
    -   ID 1221480: The Path loss estimated with and without Power Control may be very different.
    -   ID 1247513: PAwR limitations: last response slot of a subevent must end 150 us before the start of the next subevent (this affects both synchronizer and advertiser); controller privacy is not supported on the synchronizer side.
    -   ID 1258605: HCI commands starting LL procedures may return "LL busy" error when LE Power Control is active.
    -   ID 1277942: Pairing may fail when a device is not in the bonding table but it is present in the resolving list.
    -   ID 1282732: Interpacket spacing in transmitter test mode is not compliant with spec.
    -   ID 1311731: Non-compliant T_IFS (less than 150 microseconds) value measured in different PDUs.
    -   ID 1313986: LE Set Random Address may return Invalid HCI Command Parameters (0x12) when used together with extended advertising commands.
    -   ID 1317265: Periodic Synchronizer establishes sync even with invalid Sync Ind PDU.
    -   ID 1338337: High packet loss rate for BIS when using LE Coded PHY.
    -   ID 1353736: PADV may fail to start if disable advertising command is given immediately after ext adv start command.
    -   ID 1357243: Possible not compliance on CIS anchor spacing in interleaved mode.
    -   ID 1381769: CIS disconnection may not be performed if LL control procedures are ongoing.
    -   ID 1384820: CIS Central wrong subevent timings.
    -   ID 1427399: High packet loss rate when using response slot 0 in PAwR.
    -   ID 1435606: Wrong time calculation when specifying long advertising intervals.
    -   ID 1447834: Sync Lost event may happen with some specific PAwR configuration.

</div>
</div>
:::


::: {.collapse}
<input type="checkbox" id="collapse-section120" aria-hidden="true">
<label for="collapse-section120" aria-hidden="true">__V1.2.0 / 05-February-2025__</label>
<div>
<div>
## Main Changes

ST Bluetooth LE stack v4.0c release:

-   New features/updates (compared to Bluetooth LE stack v4.0b):
    -  Not applicable
-   Solved issues (compared to Bluetooth LE stack v4.0b):
    -   ID 1364324: Invalid opcode can trigger invalid Error Response PDU causing HW fault if Mem Buffer pool is poisoned.
    -   ID 1358179: Valid IRK sent during bonding procedure, even if own address is not a resolvable private address.
    -   ID 1358150: Device got stuck when receive Conn Ind with Connection Interval.
    -   ID 1357329: BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES is not up to date.
    -   ID 1357300: Connection from PAwR not possible if Central is using random address.
    -   ID 1354339: RPA change not synchronized with data change.
    -   ID 1351775: Not able to report advertising packets from multiple advertising sets using RPA.
    -   ID 1351748: Legacy Pairing not working on Peripheral if RPA is generated by the controller.
    -   ID 1198031: On GAP layer handle for advertising sets cannot be greater than or equal to NumOfAdvDataSet.
    -   ID 1195282: LL_PERIODIC_SYNC_IND PDU accepted even if Controller is already synchronized or synchronizing.
    -   ID 1356939: CIG_Sync_Delay is not correctly computed in case of interleaved CISes
    -   ID 1365521: Cannot restore to "no preferred PHY" with hci_le_set_default_phy command
    -   ID 1369496: Connection from PAwR not possible if Synchronized device is using static random address
    -   ID 1372261: No PaWR transmission when subinterval times are too tight
    -   ID 1376376: Connection from PAwR not possible if a PAST procedure is executed
    -   ID 1376394: Connection with PAwR are not allowed when PADV or PSCN device use the Controller Privacy
    -   ID 1381565: Starting extended ADV with own_address_type=0x01  is allowed even if a Random Address is not configured yet
    -   ID 1384011: Synchronization may be lost after attempting to establish a connection with PAwR
    -   ID 1384821: Peripheral CIS skips RX subevents
    -   ID 1365599: Failure of PAST procedure by scanner when PAWR is on going
    -   ID 1369495: Error returned when enabling more than one Advertising set

-   Known limitations:
    -   ID 600131: Erasing the SDB through the aci_gap_clear_security_db command shall be avoided during intense radio activities (also when a connection is active).
    -   ID 974202: Wrong data reported when ExtendedHeaderLength are less than right value.
    -   ID 1074817: Different advertising filter policies are allowed among different adverting sets. It should be forbidden according to GAP specifications.
    -   ID 1164880: Some requirements for the Access Address generation are not implemented.
    -   ID 1166170: Not possible to specify Mode 1 Level 4 requirements for a GATT characteristic.
    -   ID 1197644: Non-optimal pre-scheduler allocation under 10 ms of connection interval.
    -   ID 1213293: The Advertiser_Address shall be checked in according to Advertiser_Address_Type value for some HCI commands
    -   ID 1221480: The Path loss estimated with and without Power Control may be very different.
    -   ID 1258605: HCI commands starting LL procedures may return "LL busy" error when LE Power Control is active.
    -   ID 1277942: Pairing may fail when a device is not in the bonding table but it is present in the resolving list.
    -   ID 1282732: Interpacket spacing in transmitter test mode is not compliant with spec.
    -   ID 1313986: LE Set Random Address may return Invalid HCI Command Parameters (0x12) when used together with extended advertising commands
    -   ID 1333960: Disconnection with "instant passed" error if stack tick not called promptly
    -   ID 1247513: PAwR limitations: last response slot of a subevent must end 150 us before the start of the next subevent (this affects both synchronizer and advertiser); controller privacy is not supported on the synchronizer side.
    -   ID 1353736: If command to stop extended advertising associated to a PAVD train is given immediately after the command to start extended advertising, the PADV may not start.
    -   ID 1317265: Periodic Synchronizer establishes sync even with invalid Sync Ind PDU
    -   ID 1338337: Higher packet lost rate for BIS when using LE Coded PHY
    -   ID 1353736: PADV may fail to start if disable advertising command is given immediately after ext adv start command
    -   ID 1357243: Possible not compliance on CIS anchor spacing in interleaved mode
    -   ID 1358692: CIS creation is not performed if Power Control and Path Loss procedure keep the CPE busy
    -   ID 1381769: CIS disconnection is not performed if Power Control and Path Loss procedure keep the CPE busy
    -   ID 1357406: Multiple ACL connections, whether or not established,  are allowed between two LE device addresses when privacy is used.

</div>
</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section110" aria-hidden="true">
<label for="collapse-section110" aria-hidden="true">__V1.1.0 / 30-October-2024__</label>
<div>
<div>
## Main Changes

ST Bluetooth LE stack v4.0b release:

-   New features/updates (compared to Bluetooth LE stack v4.0):
    -   Added support for LTK request event bypass for management at application level (by writing 0x01 with ACI_HAL_WRITE_CONFIG_DATA at offset 0xD2).
    -   Added new callback BLE_STACK_ProcessRequest() to know when stack tick should be called.
    -   Added option to disable automatic generation of RPA (by writing 0x00 with ACI_HAL_WRITE_CONFIG_DATA at offset 0x33)
    -   Sent ACI_HAL_FW_ERROR_EVENT when it is not possible to allocate a radio task (error type 0x0A)
    -   Improved scan procedure in order to optimize scan efficiency.
    -   Added command ACI_L2CAP_SEND_FLOW_CONTROL_CREDITS
-   Solved issues (compared to Bluetooth LE stack v4.0):
    -   ID 1165728: Fixed issue related to GATT Indications/Notifications sent to Upper layer even when received with insufficient security level.
    -   ID 1324048: Aligned the HCI LE CONNECTION UPDATE's modularity to ACI GAP START CONNECTION UPDATE's one
    -   ID 1335303: Fixed issue with HCI LE Set Event mask command, not correctly masking events with Host+Controller configuration.
    -   ID 1284129: Sporadic ADV Data corruption in PAWR scenarios
    -   ID 1284159, 1286588: Not expected status error returned by HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA
    -   ID 1284313: Data provided on time by the Host for a PAwR subevent may be ignored when received from the Controller after the TX of the subevent has been programmed.
    -   ID 1288472: Fix corruption of first byte of PADV subevent data, happening because  "too late" error was not returned.
    -   ID 1317805: Fix problem causing missed HCI_LE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_EVENT with some specific configurations.
    -   ID 1335400: Fixed issue with HCI LE Extended Create Connection v2 command, returning an "invalid command parameter" error the second time it was called.
    -   ID 1288139: Fixed sequence number misalignment on CIG.
    -   ID 1309634: Fixed time conversion for long intervals used in ISOAL/BIG procedures, which was causing wrong timestamps.
    -   ID 1327059: Fixed wrong error code returned if an unexpected response is received by Central after it has sent a CIS_REQ PDU
    -   ID 1335915: Minor fix to avoid that a function could get stuck when too many radio events are skipped and ISO channels are used.
    -   ID 1336417: No error was returned when trying to allocate more CISes than supported.
    -   ID 1338913: Fixed missed packets on peripheral device in CIS scenarios
    -   ID 1333091: Fixed SMP security level upgrade request on Central device
    -   ID 1336195: Fixed case of reconnection with a bonded device preventing pairing with other devices in case of SC pairing.
    -   ID 1311228: Fixed case of device not returning the Database Out of Sync error.
-   Known limitations:
    -   ID 600131: Erasing the SDB through the aci_gap_clear_security_db command shall be avoided during intense radio activities (also when a connection is active).
    -   ID 974202: Wrong data reported when ExtendedHeaderLength are less than right value.
    -   ID 1074817: Different advertising filter policies are allowed among different adverting sets. It should be forbidden according to GAP specifications.
    -   ID 1164880: Some requirements for the Access Address generation are not implemented.
    -   ID 1166170: Not possible to specify Mode 1 Level 4 requirements for a GATT characteristic.
    -   ID 1197644: Non-optimal pre-scheduler allocation under 10 ms of connection interval.
    -   ID 1198031: GAP handles for advertising sets cannot be greater than or equal to NumOfAdvDataSet.
    -   ID 1221480: The Path loss estimated with and without Power Control may be very different.
    -   ID 1258605: HCI commands starting LL procedures may return "LL busy" error when LE Power Control is active.
    -   ID 1277942: Pairing may fail when a device is not in the bonding table but it is present in the resolving list.
    -   ID 1282732: Interpacket spacing in transmitter test mode is not compliant with spec.
    -   ID 1313986: LE Set Random Address may return Invalid HCI Command Parameters (0x12) when used together with extended advertising commands
    -   ID 1333960: Disconnection with "instant passed" error if stack tick not called promptly
    -   ID 1247513: PAwR limitations: last response slot of a subevent must end 150 us before the start of the next subevent (this affects both synchronizer and advertiser); controller privacy is not supported on the synchronizer side.
    -   ID 1354339: Issue with hci_le_set_data_related_address_changes command: RPA change not synchronized with change of advertising data
    -   ID 1353736: If command to stop extended advertising associated to a PAVD train is given immediately after the command to start extended advertising, the PADV may not start.

</div>
</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section100" aria-hidden="true">
<label for="collapse-section100" aria-hidden="true">__V1.0.0 / 05-June-2024__</label>
<div>
<div>
## Main Changes

ST Bluetooth LE stack v4.0 release:

-   New features/updates (compared to Bluetooth LE stack v3.x)
    -   Added Periodic Advertising with Responses (PAwR) support with
        associated new commands and events.
    -   Updated event management policy compared to previous ST
        Bluetooth LE stack v3.x releases.
    -   Added Advertising Coding selection feature.
    -   Added Encrypted Advertising Data
    -   Reviewed overall security APIs (not backward compatible with Bluetooth LE
        stack v3.x)
    -   Add a way to selectively accept/reject pairing requests from
        either peer Central or Peripheral (known as Pairing Response
        mode)
    -   Set default IO capabilities to NoInputNoOutput and MITM
        protection to NotRequired
    -   Harmonization of L2CAP COS channels that addressed the request
        to use internal mem buffers to handle both LE-CFC and ECFC
        channels
    -   Added new L2CAP APIs to make their names homogeneous and
        consistent for all commands and events
    -   Added a proprietary command (aci_gap_set_le_event_mask) to allow
        setting the LE event mask preserving the events needed by the
        Host
    -   Moved ACI_HAL_WRITE_RADIO_REG and ACI_HAL_READ_RADIO_REG outside
        of Bluetooth LE stack library
    -   Added end_of_radio_activity_event called directly from ISR
        context
    -   Added Periodic Advertising ADI support
    -   Reviewed Periodic advertising slot length
    -   Reviewed ISOAL & BIG/BIS & CIG/CIS modules
    -   Removed aci_hal_tone_start() from library
    -   Removed ACI GAP commands to handle Periodic Advertising and
        Periodic Advertising Sync Transfer modes and procedures:
        -   HCI commands are used to handle Periodic Advertising and
            Periodic Advertising Sync Transfer modes and procedures.
    -   Removed ACI_GAP_SET_EVENT_MASK command
    -   Added two new error codes: BLE_ERROR_TOO_LATE and
        BLE_ERROR_TOO_EARLY (required by PAwR)
    -   Added new modular configuration option
        CFG_BLE_CONTROLLER_PERIODIC_ADV_WR_ENABLED for
        enabling/disabling Periodic Advertising with Responses support.
    -   Removed CFG_BLE_EATT_ENABLED modular configuration option.
    -   Added new Bluetooth LE stack initialization parameters:
        -   NumOfSubeventsPAwR: Maximum number of Periodic Advertising
            with Responses subevents.
        -   MaxPAwRSubeventDataCount: Maximum number of subevent data
            that can be queued in the controller.
        -   NumOfSyncBIG: Maximum number of slots for synchronizing to a
            Broadcast Isochronous Group.
        -   NumOfBrcBIG: Maximum number of slots for synchronizing to a
            Broadcast Isochronous Stream.
        -   NumOfSyncBIS: Maximum number of slots for synchronizing to a
            Broadcast Isochronous Stream.
        -   NumOfBrcBIS: Maximum number of slots for broadcasting a
            Broadcast Isochronous Stream.
        -   NumOfCIG: Maximum number of Connected Isochronous Groups.
        -   NumOfCIS: Maximum number of Connected Isochronous Streams.
    -   Renamed Bluetooth LE stack initialization parameter
        WhiteListSizeLog2 as FilterAcceptListSizeLog2.
    -   Removed aci_gatt_srv_init() API and moved to GATT profile
        managed externally (aci_gatt_srv_profile_init()).
    -   Removed some parameters on aci_gap_init() API
    -   Added new aci_gap_profile_init() API.
    -   Renamed some commands and events compared to previous Bluetooth
        LE stack v3.x
    -   Modified some GATT commands and events by adding the CID
        parameter to support both Unenhanced and Enhanced channels.
    -   Removed GATT commands for EATT channels: they have been replaced
        by corresponding GATT commands modified by adding the CID
        parameter.
-   Solved issues (compared to Bluetooth LE stack v3.x):
    -   ID 1055406: Periodic advertising sync ends abnormally. Sometimes
        the scanner, synchronized with a periodic advertiser, ends
        sending advertising reports to the application.
    -   ID 1127696: Missed SDU in BIG Synchronize
    -   ID 1127085: Number of simultaneous supported BIS (currently 2)
        not matching customer requirement (set to 4)
    -   ID 1166290: Discovery procedures not excluded in Observer role;
        Discoverability mode not excluded in Broadcaster role
    -   ID 1166716: Operation parameter is ignored in both the LE Set
        Extended Advertising Data and LE Set Periodic Advertising Data
        commands
    -   ID 1171561: Command Disallowed is not returned when a data path
        not allowed (with BN=0) is configured
    -   ID 1191988: Missing
        HCI_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_EVENT
    -   ID 1197578: Issue in ACI_HAL_GET_LINK_STATUS when connection is
        established with Extended ADV Commands
    -   ID 1214606: Corruption of advertising context during long run
        tests
-   Known limitations:
    -   ID 974202: Wrong data reported when ExtendedHeaderLength are
            less than right value.
    -   ID 1074817: Different advertising filter policies are
            allowed among different adverting sets. It should be
            forbidden according to GAP specifications.
    -   ID 1164880: Some requirements for the Access Address generation are not implemented.
    -   ID 1165728, 1165731: GATT Notifications/Indications sent to Upper layer even when
        received with insufficient security level: the link security requirements when receiving the
            indications shall be verified directly by the application
            layer that may then discard those not satisfying the minimum
            requirements.
    -   ID 1166170: Not possible to specify Mode 1 Level 4 requirements for a GATT characteristic.
        - Characteristic properties shall be redefined at application level.
    -   ID 1197644: Non-optimal pre-scheduler allocation under 10 ms of connection interval
    -   ID 1198031: GAP handles for advertising sets cannot be greater than or equal to NumOfAdvDataSet
    -   ID 1221480: The Path loss estimated with and without Power Control may be very different.
    -   ID 1258605: HCI commands starting LL procedures may return "LL busy" error when LE Power Control is active.
    -   ID 1277942: Pairing may fail when a device is not in the bonding table but it is present in the resolving list.
    -   ID 1286651: Non-optimal scan performance when lots of advertising packets are received.
    -   ID 1247513: PAwR limitations: last response slot of a subevent must end 150 us before the start of the next subevent (this affects both
        synchronizer and advertiser); controller privacy is not supported on the synchronizer side.
    -   ID 1284159, 1286588: Not expected status error returned by HCI_LE_SET_PERIODIC_ADVERTISING_RESPONSE_DATA
    -   ID 1284313: Data provided on time by the Host for a PAwR subevent may be ignored when received from the Controller after the TX of the subevent has been programmed

</div>
</div>
:::

:::
:::

<footer class="sticky">
For complete documentation on STM32WB0x,visit: [[www.st.com/stm32WB0](http://www.st.com/stm32WB0)]

*This release note uses up to date web standards and, for this reason, should not be opened with Internet Explorer but preferably with popular browsers such as Google Chrome, Mozilla Firefox, Opera or Microsoft Edge.*
</footer>
