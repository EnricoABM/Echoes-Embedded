import os
from dotenv import load_dotenv
load_dotenv()
pioEnv = os.getenv('PIO_ENV') or ''
if pioEnv.lower() == "dev":
    print('-DDEV_BUILD')
if pioEnv.lower() == "verbose":
    print('-DCORE_DEBUG_LEVEL=5')
    print('-DDEV_BUILD')
    print('-DLWIP_DEBUG=1')
    print('-DLWIP_HTTPD_DEBUG=LWIP_DBG_ON')
    print('-DLWIP_TCP_DEBUG=LWIP_DBG_ON')
    print('-DLWIP_IP_DEBUG=LWIP_DBG_ON')
    print('-DHTTP_DEBUG=1')
