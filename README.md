# Container builds for BIRD

This is an **unofficial** channel, provided as-is without any warranty.
If you have the funds, we recommend you contact CZ.NIC and purchase a [support plan](https://bird.network.cz/?support) to support their efforts.

## Usage

This repository builds a container image containg the latest BIRD release that is present in EPEL.

**Example:**
```
$ podman run ghcr.io/sonix-network/bird:2 --version
BIRD version 2.15.1
```

The image build uses four tag families:
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
      - '-u'
      - '998'
      - '-c'
      - '/run/bird/bird.conf'
      - '-s'
      - '/run/bird/bird.ctl'
      - '-P'
      - '/run/bird/bird.pid'
    securityContext:
      capabilities:
        add:
          - NET_ADMIN
          - NET_BROADCAST
          - NET_RAW
          - NET_BIND_SERVICE
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
