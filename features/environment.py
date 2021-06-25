NMAP_PATH = "./ft_nmap"

def before_scenario(context, scenario):
    context.args = [NMAP_PATH]
