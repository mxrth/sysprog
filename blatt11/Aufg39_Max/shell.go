package main

import (
    "fmt"
    "bufio"
    "strings"
    "os/user"
    "os/exec"
    "os"
    "path/filepath"
)



func main() {

    builtins := map[string]func([]string){
	"cd": handle_cd,
	"exit": handle_exit,
    }

    initShell()


    for {
	echoPrompt()

	bio := bufio.NewReader(os.Stdin)
	command, err := bio.ReadString('\n')


	parts := strings.Fields(command)

	cmdName := parts[0]
	args := parts[1:]

	handleFn, isBuiltin := builtins[cmdName]

	if isBuiltin {
	    handleFn(args)
	    continue
	}

	command, err = exec.LookPath(cmdName)
	if err != nil {
	    fmt.Println("gosh! Command not found...")
	    continue;
	}


	cmd := exec.Command(command, args...)

	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	cmd.Run()
    }
}

func initShell() {
    //clear terminal
    fmt.Print("\033[H\033[2J")
}

func echoPrompt() {
    var username string = ""
    user, err := user.Current()
    if err == nil {
	username = user.Username
    }
    host, err := os.Hostname()
    wd, err := os.Getwd()
    wd = filepath.Base(wd)

    fmt.Printf("%s@%s %s$ ", username, host, wd);
}


func handle_cd(args []string) {
    if len(args) == 0 {
	fmt.Println("changing to home not implemented...")
	return
    }
    absPath, err := filepath.Abs(args[0])
    if err != nil {
	fmt.Println("gosh! cd: cannot change working directory")
	return
    }
    err = os.Chdir(absPath)
    if err != nil {
	fmt.Println("gosh! cd: cannot change directory to ", absPath)
    }
}

func handle_exit(args []string) {
    os.Exit(0)
}



