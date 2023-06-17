pub mod server;
use crate::server::chat_server::{broadcast_server};

#[tokio::main] // for Future execution in main function
async fn main() {
    
    broadcast_server().await;
    
}
