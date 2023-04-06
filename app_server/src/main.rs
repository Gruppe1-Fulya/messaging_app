pub mod server;
use crate::server::chat_server::{ group_chat, p2p_chat };

#[tokio::main] // for Future execution in main function
async fn main() {
    
    group_chat().await;
    
}
