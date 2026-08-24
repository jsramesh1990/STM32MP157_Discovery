`m4-firmware` can be useful, but **you should not keep both `cortex-m4` and `m4-firmware` if they do the same job**.

For your project, I would give them **different responsibilities** if you want to keep both.

Use:

```text
yocto/meta-energy-sensor/recipes-firmware/
├── cortex-m4/
│   └── cortex-m4.bb
│
└── m4-firmware/
    └── m4-firmware.bb
```

The distinction is:

```text
cortex-m4/
    → Builds the Cortex-M4 firmware from source

m4-firmware/
    → Packages/deploys the already-built M4 firmware
```

The flow becomes:

```text
cortex-m4/
STM32MP157_Discovery/cortex-m4/
        │
        │ source code
        ▼
cortex-m4.bb
        │
        │ compile
        ▼
stm32mp157-m4.elf
        │
        ▼
m4-firmware.bb
        │
        │ package
        ▼
/lib/firmware/
        │
        ▼
Linux remoteproc
        │
        ▼
Cortex-M4
```

However, **for your current GitHub project, I recommend not having both yet**. It adds unnecessary duplication.

Since your actual source is already:

```text
STM32MP157_Discovery/cortex-m4/
```

the clean structure is:

```text
yocto/meta-energy-sensor/recipes-firmware/
└── cortex-m4/
    └── cortex-m4.bb
```

Then the recipe itself builds and installs the firmware:

```text
cortex-m4 source
      ↓
cortex-m4.bb
      ↓
build
      ↓
stm32mp157-m4.elf
      ↓
/lib/firmware/
```

### When would `m4-firmware` make sense?

If later your project has **prebuilt firmware** supplied separately, for example:

```text
prebuilt/
└── stm32mp157-m4.elf
```

then you could introduce:

```text
recipes-firmware/
├── cortex-m4/
│   └── cortex-m4.bb
│
└── m4-firmware/
    ├── m4-firmware.bb
    └── files/
        └── stm32mp157-m4.elf
```

Then:

```text
cortex-m4.bb
    → Compile source firmware

m4-firmware.bb
    → Package an existing/prebuilt ELF
```

For your current project, though, **keep `m4-firmware` out** unless you specifically want a separate prebuilt-firmware packaging path.

