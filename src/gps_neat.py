import pandas as pd
import numpy as np
import time
import datetime
import sys

def func(s):
	return int(time.mktime(datetime.datetime.strptime(s[0:-3], '%d%m%y%H%M%S').timetuple()))
def func2(s):
	return "{0:.5f}".format(s)
def func3(s):
	return "{0:.3f}".format(s*1.852)
# read GPS data
df = pd.read_csv(sys.argv[1], header=None, names=['flag','time','A','longitude','B','latitude','C', 'speed', 'D', 'date', 'E', 'F', 'G'], dtype={'time': str, 'date':str})
# drop some columns
df.drop(df.columns[[0,2,4,6,8,10,11,12]], axis=1, inplace=True)
# concatenate date and time
df['timestamp'] = df['date'] + df['time']
# reorder and drop some columns
df = df[['timestamp', 'longitude', 'latitude', 'speed', 'time', 'date']];
df.drop(df.columns[[4,5]], axis=1, inplace=True)
# convert time string to timestamp
df['timestamp'] = df.timestamp.apply(func)
# clean up
df['longitude'] = df.longitude.apply(func2)
df['latitude'] = df.latitude.apply(func2)
df['speed'] = df.speed.apply(func3)
# print to csv file
df.to_csv(path_or_buf=sys.argv[2],index=False)