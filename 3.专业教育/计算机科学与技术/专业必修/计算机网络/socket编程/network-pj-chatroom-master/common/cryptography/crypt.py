from random import randint

from common.cryptography import prime
from common.config import get_config
from common.util import long_to_bytes
import hashlib

config = get_config()
base = config['crypto']['base']
modulus = config['crypto']['modulus']
secret = prime.generate_big_prime(12)

my_secret = base ** secret % modulus


def get_shared_secret(their_secret):
    return hashlib.sha256(long_to_bytes(their_secret ** secret % modulus)).digest()
