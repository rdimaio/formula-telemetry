-- Create database
-- CREATE DATABASE sensor_data;

-- Extend database with TimescaleDB
CREATE EXTENSION IF NOT EXISTS timescaledb;

-- Create table
CREATE TABLE IF NOT EXISTS vehicle_data (
  time           TIMESTAMPTZ      NOT NULL,
  speed          DOUBLE PRECISION NULL,
  rpm            DOUBLE PRECISION NULL,
  steering_pos   DOUBLE PRECISION NULL,
  throttle_pos   DOUBLE PRECISION NULL,
  brake_pressure DOUBLE PRECISION NULL
);

-- Create hypertable partitioned by `time` column (TimescaleDB)
SELECT create_hypertable('vehicle_data', 'time', if_not_exists => TRUE);

-- Create user for reading data from Grafana
CREATE USER grafanareader WITH PASSWORD 'password';
 GRANT USAGE ON SCHEMA public TO grafanareader;
 GRANT SELECT ON ALL TABLES IN SCHEMA public TO grafanareader;
 
-- Create user for writing data to the database
CREATE USER datawriter WITH PASSWORD 'password';
 GRANT USAGE ON SCHEMA public TO datawriter;
 GRANT INSERT ON ALL TABLES IN SCHEMA public TO datawriter;