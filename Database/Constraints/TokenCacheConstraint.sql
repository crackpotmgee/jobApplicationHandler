ALTER TABLE token_cache 
ADD CONSTRAINT unique_user_service 
UNIQUE (service_name, user_id);