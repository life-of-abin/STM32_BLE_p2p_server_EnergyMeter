# STM32 BLE P2P Server – EPC5110D Energy Meter Modbus RTU Bridge (Raw Data Mode)

## Short Description
STM32WB09KE BLE P2P server that reads 60 Modbus RTU registers from an EPC5110D energy meter via RS-485 to TTL converter and sends the raw register values (hex) as BLE notifications.

## Long Description
This project builds on ST’s `BLE_p2pServer` example for the STM32WB series, integrating Modbus RTU communication to an **EPC5110D** three-phase panel-mount energy meter.  
The STM32 communicates with the meter through an **RS-485 to TTL converter**, retrieving a block of **60 consecutive Modbus holding registers** in a single request.  
Instead of parsing or scaling the data on the MCU, the firmware transmits the **raw 16-bit register values (in hex)** via BLE notifications.  

Parsing into floating-point engineering values is left to the BLE client application, which can use the provided **Modbus register map** for decoding.

## Key Features
- BLE 5.0 P2P Server on STM32WB09KE  
- RS-485 to TTL Modbus RTU interface to EPC5110D  
- Single request fetch of 60 consecutive holding registers  
- Transmission of unparsed raw register values in hex via BLE notifications  
- Modbus register mapping includes Watts, VAR, PF, VA, Voltage (VLL/VLN), Current, Frequency, and Energy  
- BLE write command triggers Modbus read cycle  
- Designed for external parsing by mobile/PC application  

## Example Register Mapping (Partial)

| Index | Address | Type  | Parameter         |
|-------|---------|-------|-------------------|
| 1     | 40101   | float | Watts Total       |
| 2     | 40103   | float | Watts R phase     |
| 3     | 40105   | float | Watts Y phase     |
| …     | …       | …     | …                 |
| 30    | 40159   | float | Wh received       |

## Technologies
- **MCU:** STM32WB09KE  
- **IDE:** STM32CubeIDE  
- **Protocols:** BLE 5.0, Modbus RTU  
- **Hardware:** EPC5110D Energy Meter, RS-485 to TTL converter

