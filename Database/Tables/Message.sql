CREATE TABLE messages (
    id SERIAL PRIMARY KEY,
    service_name VARCHAR(100),
    service_message_id VARCHAR(255) UNIQUE NOT NULL,
    sender VARCHAR(100),
    recipient VARCHAR(100),
    content TEXT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);