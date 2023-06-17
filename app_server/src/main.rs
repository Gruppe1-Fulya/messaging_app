pub mod database;
pub mod server;
use crate::server::chat_server::{broadcast_server};

#[tokio::main] // for Future execution in main function
async fn main() {
    
    let res = database::database::get_port_number_from_id("enaciodabasi@outlook.com".to_string());
    
    broadcast_server().await;
    
}
