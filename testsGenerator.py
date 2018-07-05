import numpy as np

def generate_test(size, name):
    values = np.random.randint(10000, size=size)
    median_requests = np.sort(np.random.randint(1, size, size=size // 10))
    input = ' '.join(np.insert(values.astype(str), median_requests, 'm')) + ' q'
    with open(name + '_in', 'w') as f:
        f.write(input)
    
    medians = map(lambda ind : np.median(values[:ind]), median_requests)
    output = ' '.join(map(lambda m : str(int(m)) if m == int(m) else str(m) , medians)) + ' '
    with open(name + '_out', 'w') as f:
        f.write(output)
    