#!/usr/bin/env python
#

import redis
import os

mydir = {
    "1460359200": {
        "dcnd1" : {
            "rtt" : 10,
            "lost": 0,
        }
    },
    "1460359260": {
        "dcnd1" : {
            "rtt" : 20,
            "lost": 1,
        }
    }
}

print mydir


# pool = redis.ConnectionPool(host='127.0.0.1', port='6379')
# r = redis.Redis(connection_pool=pool)
# pipe = r.pipeline()
# pipe.set('one', 'first')
# pipe.set('two', 'second')
# pipe.execute()






