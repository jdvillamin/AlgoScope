FROM python:3.11-slim

# gcc is required at runtime to compile user-submitted C
RUN apt-get update && apt-get install -y --no-install-recommends \
        gcc libc6-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Install Python deps first for layer caching
COPY backend/requirements.txt ./backend/requirements.txt
RUN pip install --no-cache-dir -r backend/requirements.txt

# Copy backend source and tracer (app.py expects ../tracer relative to backend/)
COPY backend/ ./backend/
COPY tracer/  ./tracer/

# Remove local dev files that should not be in the image
RUN rm -f ./backend/.env ./backend/algoscope.db

WORKDIR /app/backend

ENV PORT=10000
EXPOSE 10000
CMD ["sh", "-c", "flask db upgrade && gunicorn -w 2 -b 0.0.0.0:$PORT app:app --timeout 30"]
