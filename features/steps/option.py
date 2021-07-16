from behave import *
from subprocess import run
import logging
global log

handler = logging.FileHandler('behave.log', mode='w')
handler.setFormatter(logging.Formatter(fmt=logging.BASIC_FORMAT))
log = logging.getLogger('behave')
log.setLevel(logging.DEBUG)
log.addHandler(handler)


@given ('the option {option}')
def use_option(context, option: str):
    context.args.append(option)

@given ('the argument {argument} with option {option}')
def use_option_with_argument(context, option: str, argument:str):
    context.args.append(option)
    context.args.append(argument)

@when('we run the program')
def run_nmap(context):
    context.program = run(context.args, text=True, capture_output=True)

@then('we get an error')
def check_error_message(context):
    log.debug(context.text)
    log.debug(context.program.stderr.strip())
    log.debug(context.text == context.program.stderr.strip())
    assert context.text == context.program.stderr.strip()

@then('we get usage')
def check_usage(context):
    log.debug(context.text)
    log.debug(context.program.stdout)
    log.debug(context.text == context.program.stdout.strip())
    assert context.text == context.program.stdout.strip()

@then('we output results')
def output_results(context):
    log.debug(context.text)
    log.debug(context.program.stdout)
    log.debug(context.text == context.program.stdout.strip())
    assert context.text == context.program.stdout.strip()

