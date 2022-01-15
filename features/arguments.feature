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

    Scenario: run '--scan' with wrong format 'test1'
        Given the argument SYN,test1 with option --scan
        When we run the program
        Then we get an error
        """
        ft_nmap: wrong format 'test1' for option '--scan'
        """

    Scenario: run '--scan' with wrong type 'a'
        Given the argument a with option --scan
        When we run the program
        Then we get an error
        """
        ft_nmap: unsupported type 'a' for option '--scan'
        """

    Scenario: run '--speedup' with wrong type 'a'
        Given the argument a with option --speedup
        When we run the program
        Then we get an error
        """
        ft_nmap: unsupported type 'a' for option '--speedup'
        """

    #Scenario: run with an argument
    #    Given the argument test1
    #    When we run the program
    #    Then we get an error
    #    """
    #    ft_nmap: extra argument 'test1'
    #    """
    #    Then we get usage
    #    """
    #    ft_nmap [--help] [--ports [NOMBRE/PLAGE]] [--dry-run] [--speedup [NOMBRE]] [--scan [TYPE]] --ip [ADRESSE]
    #    """

    #Scenario: run with the --help option
    #    Given the option --help
    #    When we run the program
    #    Then we get usage
    #        """
    #        ft_nmap [--help] [--ports [NOMBRE/PLAGE]] [--dry-run] [--speedup [NOMBRE]] [--scan [TYPE]] --ip [ADRESSE]
    #        """
