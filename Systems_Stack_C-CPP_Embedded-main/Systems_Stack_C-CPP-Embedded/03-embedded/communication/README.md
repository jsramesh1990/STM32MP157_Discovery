# COMMUNICATION PROTOCOLS

## UART (Universal Asynchronous Receiver/Transmitter)

### Characteristics
- **Asynchronous** (no clock line)
- **Point-to-point** (2 devices)
- **Full duplex** (send/receive simultaneously)

### UART Signals
| Signal | Direction | Purpose |
|--------|-----------|---------|
| TX | Out | Transmit data |
| RX | In | Receive data |
| GND | - | Common ground |

### Baud Rate

Baud Rate = bits per second

Common rates: 9600, 19200, 38400, 115200, 921600

Bit time = 1 / Baud Rate
Example: 9600 baud → 104.16 microseconds per bit
text


### UART Frame

Start Bit Data Bits (5-9) Parity (optional) Stop Bit(s)
↓ ↓ ↓ ↓
┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───────┐
│ 0 ││ 1 ││ 0 ││ 1 ││ 0 ││ 0 ││ 1 ││ 1 ││ 0 ││ 1 │
└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───────┘
LOW 8-bit data (0x5A) HIGH
text


## SPI (Serial Peripheral Interface)

### Characteristics
- **Synchronous** (has clock)
- **Full duplex**
- **Multi-slave** (multiple devices)

### SPI Signals
| Signal | Direction | Purpose |
|--------|-----------|---------|
| SCK | Master out | Clock |
| MOSI | Master out → Slave in | Data |
| MISO | Slave out → Master in | Data |
| SS/CS | Master out | Slave select |

### SPI Modes
| Mode | CPOL | CPHA | Description |
|------|------|------|-------------|
| 0 | 0 | 0 | Idle low, sample rising edge |
| 1 | 0 | 1 | Idle low, sample falling edge |
| 2 | 1 | 0 | Idle high, sample falling edge |
| 3 | 1 | 1 | Idle high, sample rising edge |

## I2C (Inter-Integrated Circuit)

### Characteristics
- **Synchronous** (clock)
- **Half duplex** (one direction at a time)
- **Multi-master, multi-slave**
- **Only 2 wires** (SDA, SCL)

### I2C Signals
| Signal | Direction | Purpose |
|--------|-----------|---------|
| SDA | Bidirectional | Data |
| SCL | Master out | Clock |

### I2C Frame

Start Address (7 bits) R/W ACK Data ACK Data ... Stop
↓ ↓ ↓ ↓ ↓ ↓ ↓
┌──┐ ┌─────────┐ ┌──┐ ┌──┐ ┌────┐ ┌──┐ ┌───┐
│S │ │ 0x50 │ │0 │ │A │ │0x55│ │A │ ... │ P │
└──┘ └─────────┘ └──┘ └──┘ └────┘ └──┘ └───┘
text


## Comparison

| Feature | UART | SPI | I2C |
|---------|------|-----|-----|
| Wires | 3 (TX,RX,GND) | 4 | 2 |
| Speed | Up to 12 Mbps | Up to 100 MHz | Up to 5 Mbps |
| Type | Asynchronous | Synchronous | Synchronous |
| Duplex | Full | Full | Half |
| Multi-slave | No | Yes (with CS) | Yes (addressing) |
| Complexity | Simple | Medium | Complex |

## Run the Code

```bash
cd Systems_Stack_C-CPP-Embedded
gcc 03-embedded-baremetal/communication/communication.c -o communication
./communication

Key Takeaways

    UART – Simple, 2-way, good for debugging

    SPI – Fast, best for sensors/displays

    I2C – 2 wires, good for multiple devices

    Baud rate must match for UART

    SPI modes must match between devices

    I2C needs pull-up resistors on SDA/SCL
