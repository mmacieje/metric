# Metric
a simple service for calculating a metric from a JSON
# Command for building
docker build . -t metric
# Command for running
docker run -it -p 9000:9000 -p 9100:9100 metric
