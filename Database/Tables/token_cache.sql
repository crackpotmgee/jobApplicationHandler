CREATE Table token_cache (
  service_name VARCHAR(100) NOT NULL,
  user_id INTEGER REFERENCES platform_user(id) ON DELETE CASCADE,
  access_token VARCHAR(1024) NOT NULL,
  refresh_token VARCHAR(1024) NOT NULL,
  expires_at TIMESTAMP WITH TIME ZONE NOT NULL,
  created_at TIMESTAMP WITH TIME ZONE DEFAULT now(),
  updated_at TIMESTAMP WITH TIME ZONE DEFAULT now()
)
ADD CONSTRAINT unique_user_service 
UNIQUE (service_name, user_id);