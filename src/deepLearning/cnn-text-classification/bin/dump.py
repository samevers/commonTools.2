#! /usr/bin/env python
import os
from pprint import pprint

def dump1(obj):
    newobj=obj
    if '__dict__' in dir(obj):
        newobj=obj.__dict__
        if ' object at ' in str(obj) and not newobj.has_key('__type__'):
            newobj['__type__']=str(obj)
        for attr in newobj:
            newobj[attr]=dump1(newobj[attr])
    return newobj
def dump(obj):
    pprint(dump1(obj))
