# A light-weight http request client    

##  Architecture 

                ┌─────────────────────────────┐
                │             GUI             │
                │          (Raylib)           │
                │   - URL input               │
                │   - Headers editor          │
                │   - Send button             │
                │   - Response viewer         │
                └─────────────┬───────────────┘
                              │
                              ▼
                ┌─────────────────────────────┐
                │       GUI Error Layer       │
                │   - Checks inputs           │
                │   - Validates headers/body  │
                │   - Passes clean params     │
                └─────────────┬───────────────┘
                              │
                              ▼
                ┌─────────────────────────────┐
                │        HTTP Wrapper         │
                │   - GetSetter/PostSetter    │
                │   - HeaderSetter            │
                │   - WriteToMemory           │
                │   - SendRequest             │
                └──────────────────────────── ┘
                              
