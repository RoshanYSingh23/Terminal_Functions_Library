import re, statistics

with open('raw_results.txt') as f:
    lines = [l.strip() for l in f if l.strip()]

results = []
times_on = []
times_off = []

for i in range(0, len(lines), 3):
    expr = lines[i]
    m_on  = re.match(r"([\d\.eE+-]+)\s+([\d\.eE+-]+)", lines[i+1])
    m_off = re.match(r"([\d\.eE+-]+)\s+([\d\.eE+-]+)", lines[i+2])
    if m_on and m_off:
        val_on, t_on   = m_on.groups()
        val_off, t_off = m_off.groups()
        results.append(f"{expr}: ON={val_on} ({t_on} ms), OFF={val_off} ({t_off} ms)")
        times_on.append(float(t_on))
        times_off.append(float(t_off))
    else:
        results.append(f"{expr}: ON={lines[i+1]}, OFF={lines[i+2]}")

if times_on:
    results.append(f"Average ON-time: {statistics.mean(times_on):.3f} ms")
    results.append(f"Average OFF-time: {statistics.mean(times_off):.3f} ms")

with open('output.txt','w') as out:
    out.write("\n".join(results))
