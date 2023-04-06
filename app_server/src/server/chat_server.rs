use tokio::{
    io::{AsyncBufReadExt, AsyncWriteExt, BufReader},
    net::TcpListener,
    sync::broadcast, 
};


pub async fn group_chat() {

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

                        tx.send((line.clone(), addr)).unwrap();
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

pub async fn p2p_chat() {
    // p2p chat will be added
}