The distinction should be:

scripts/
    → Build, clean, deploy and complete-project automation

linux/scripts/
    → Runtime Linux power/sensor/suspend/wakeup tests

Make them executable:

cd STM32MP157_Discovery/scripts

chmod +x build_all.sh
chmod +x clean_all.sh
chmod +x collect_logs.sh
chmod +x deploy_all.sh
chmod +x run_tests.sh

Then the intended workflow is:

                    Developer
                        │
                        ▼
                 build_all.sh
                        │
            ┌───────────┼───────────┐
            ▼           ▼           ▼
         Cortex-M4    Linux       DT
            │           │           │
            └───────────┼───────────┘
                        ▼
                 deploy_all.sh
                        │
                        ▼
                  STM32MP157-DK
                        │
                        ▼
                  run_tests.sh
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
     power_test     sensor_test   suspend/wakeup
          │             │             │
          └─────────────┼─────────────┘
                        ▼
                collect_logs.sh
                        │
                        ▼
                     logs/

One thing I'd change from the earlier structure: don't create a logs/ directory manually in the GitHub repository. Let collect_logs.sh create it at runtime, and add logs/ to .gitignore. This keeps generated runtime data out of your source repository.
