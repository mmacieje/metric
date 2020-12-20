import sys
import json
import hashlib 

def load_json(file_name):
    with open(file_name) as f:  
        return json.loads( f.read() )

def calculate_metric(data):
    data_2_digest = ''
    for r in data['data']:
        data_2_digest += r['signature']
    return {'metric': { 'signature': hashlib.sha256( data_2_digest.encode() ).hexdigest(),
                        'number-of-items': int( len(data['data']) )}}

def compare_metric(m1, m2):
    return ( m1['metric']['signature'] == m2['metric']['signature'] \
        and m1['metric']['number-of-items'] == m2['metric']['number-of-items'] )

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python3 verify.py dataFile') 
        print('     or: python3 verify.py dataFile, metricFile') 
        exit(1)
        
    data = load_json(sys.argv[1])
    
    if len(sys.argv) == 2:
        metric_file_name = sys.argv[1].replace('tc.json', 'metric.json')
    else:
        metric_file_name = sys.argv[2]


    print(metric_file_name)
    metric = load_json(metric_file_name)
    compare_metric(metric, calculate_metric(data))

    result = {
        'data': sys.argv[1],
        'metric': metric_file_name,
        'status': 'VALID' if compare_metric(metric, calculate_metric(data)) else 'INVALID'
    }

    print( json.dumps(result) )
