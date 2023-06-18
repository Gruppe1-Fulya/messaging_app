pub mod database;
pub mod server;
pub mod main_server;
use database::database::clear_user_table;
use main_server::main_server::init_main_server;

use crate::server::chat_server::{broadcast_server};


#[tokio::main] // for Future execution in main function
async fn main() {
    
    clear_user_table();

    init_main_server().await;
    
}
