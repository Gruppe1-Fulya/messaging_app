/**
 * Authord: Nihat Akin
 */
use tokio::{
    io::{AsyncBufReadExt, AsyncWriteExt, BufReader},
    net::TcpListener,
    sync::broadcast, 
};
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Clone)]
struct MessageRequest {
    message: String,
    addr: std::net::SocketAddr,
}


pub async fn broadcast_server() {

    // TCP Server listener
    let listener = TcpListener::bind("localhost:3000").await.unwrap();
    let (tx, _rx) = broadcast::channel(10);

    loop {
        // Accepting Connections
        let (mut socket, addr) = listener.accept().await.unwrap();
        println!("[New Client] Address: {:?}", addr);
        let tx = tx.clone();
        let mut rx = tx.subscribe();

        tokio::spawn(async move {
            let (reader, mut writer) = socket.split();
            let mut reader = BufReader::new(reader);
            
            let mut line = String::new();            

            loop {
                tokio::select! {
                    result = reader.read_line(&mut line) => {
                        if result.unwrap() == 0 {
                            break;
                        }

                        let line_json = MessageRequest {
                            message: line.clone(),
                            addr: addr,
                        };

                        let mut json_string = serde_json::to_string(&line_json).unwrap();

                        tx.send((json_string.clone(), addr)).unwrap();
                        json_string.clear();
                        line.clear();
                    }
                    result = rx.recv() => {
                        let (msg, other_addr) = result.unwrap();
                        if addr != other_addr {
                            println!("\nSender Address: {:?}", other_addr);
                            writer.write_all(msg.as_bytes()).await.unwrap();   
                        }
                    }
                }
            }
        });
    }
}
