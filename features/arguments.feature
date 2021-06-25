Feature: Arguments

    Scenario: run with an invalid option
        Given the option -z
         When we run the program
         Then we get an error
            """
            ft_nmap: invalid option -- 'z'
            """

    Scenario: run with the help option
        Given the option -h
         When we run the program
         Then we get usage
            """
            ft_nmap -h --help [--ports [NOMBRE/PLAGE]]--ip ADRESSE IP [--speedup [NOMBRE]] [--scan [TYPE]]
            """
