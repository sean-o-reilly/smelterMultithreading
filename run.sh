export ASAN_OPTIONS=detect_leaks=1
cmd.exe /c start wt.exe -d "$(wslpath -w "$(pwd)")" wsl.exe ./main 
# Forces run in current directory, weird WSL thing

read -p "ENTER to exit..."
