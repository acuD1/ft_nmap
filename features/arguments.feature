Feature: Arguments

    Scenario: run with an invalid option
        Given the option -z
         When we run the program
         Then we get an error
            """
            ft_nmap: invalid option -- 'z'
            """

    Scenario: run with an invalid long option
        Given the option --zzz
        When we run the program
        Then we get an error
            """
            ft_nmap: unrecognized option '--zzz'
            """

    Scenario: run with a long option without argument
        Given the option --ip
        When we run the program
        Then we get an error
            """
            ft_nmap: option '--ip' requires an argument
            See the output of ft_nmap --help for a summary of options.
            """

    # Scenario: run with an option without argument
    #     Given the option -t
    #     When we run the program
    #     Then we get an error
    #         """
    #         ft_nmap: option requires an argument -- 't'
    #         See the output of ft_nmap --help for a summary of options.
    #         """

    Scenario: run with the --help option
        Given the option --help
        When we run the program
        Then we get usage
            """
            ft_nmap [--help] [--ports [NOMBRE/PLAGE]] --ip ADRESSE IP [--speedup [NOMBRE]] [--scan [TYPE]]
            """
