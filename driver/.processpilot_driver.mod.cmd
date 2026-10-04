savedcmd_processpilot_driver.mod := printf '%s\n'   processpilot_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > processpilot_driver.mod
