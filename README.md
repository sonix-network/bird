# Container builds for BIRD

This repository builds a container image containg the latest BIRD release that is present in EPEL.

It has four tags:
 - `MAJOR` - e.g. `2`
 - `MAJOR.MINOR` - e.g. `2.15`
 - `vVERSION` - e.g. `v2.15.1-1`
 - `latest`

Use as you see fit.

Example Kubernetes pod definition:

```yaml
 containers:
    # BIRD route server
  - name: bird
    image: ghcr.io/sonix-network/bird:2.15
    args:
      - '-f'
      - '-c'
      - '/run/bird/bird.conf'
      - '-s'
      - '/run/bird/bird.ctl'
    securityContext:
      runAsUser: 998
      allowPrivilegeEscalation: false
    volumeMounts:
    - mountPath: /run/bird/
      name: shared-volume

    # BIRD Prometheus exporter
  - name: exporter
    image: ghcr.io/czerwonk/bird_exporter:1.4.3
    args:
    - '-bird.v2'
    - '-bird.socket'
    - '/run/bird/bird.ctl'
    - '-web.listen-address'
    - ':9324'
    volumeMounts:
    - mountPath: /run/bird/
      name: shared-volume
```
