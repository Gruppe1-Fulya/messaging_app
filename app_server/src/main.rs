<<<<<<< HEAD
use tokio::{net::TcpListener, io::{ AsyncWriteExt, BufReader, AsyncBufReadExt}};


#[tokio::main]
async fn main() {
    
    let listener = TcpListener::bind("localhost:8080").await.unwrap();

    loop {
    
        let (mut socket, _addr) = listener.accept().await.unwrap();
        tokio::spawn(async move{
            let (reader, mut writer) = socket.split();

            let mut reader = BufReader::new(reader);
            let mut line = String::new();
            loop {
            
                let bytes_read = reader.read_line(&mut line).await.unwrap();
                if bytes_read == 0{
                    break;
                }
            
                writer.write_all(line.as_bytes()).await.unwrap();
                line.clear();
            }
        });
        
    }
}

=======
pub mod server;
use crate::server::chat_server::{ group_chat, p2p_chat };

#[tokio::main] // for Future execution in main function
async fn main() {
    
    group_chat().await;
    
}
>>>>>>> a6c24ec378441f97a8c9bfa8baf3bc91b66b58b8
