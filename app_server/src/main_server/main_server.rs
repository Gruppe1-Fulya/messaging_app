use std::{net::TcpStream, io::Write, f32::consts::E};

use tokio::{
    io::{AsyncBufReadExt, AsyncWriteExt, BufReader},
    net::{TcpListener},
    sync::broadcast,
};
use serde::{Deserialize, Serialize};
use serde_json;

use crate::database::{self, database::{get_port_number_from_id, insert_new_user_to_db}};

#[derive(Debug, Deserialize, Serialize, Clone)]
struct MessageInfo
{
    data: String,
    sender: String,
    receiver: String,
    addr : String
}


pub async fn init_main_server()
{
    let listener : tokio::net::TcpListener = TcpListener::bind(
        "localhost:3000"
    ).await.unwrap();

    let (tx, _) = broadcast::channel::<MessageInfo>(10);

    loop 
    {
        let (socket, _) = listener.accept().await.expect("Failed to accept connection.");

        let tx = tx.clone();
        
        let mut msg_optional: Option<MessageInfo> = None;

        tokio::spawn(async move{

            let (reader, mut writer) = tokio::io::split(socket);
            
            let mut reader = BufReader::new(reader);

            let mut line_read = String::new();

            while let Ok(bytes_read) = reader.read_line(&mut line_read).await{
                if bytes_read == 0
                {
                    return;
                }            
                if let Ok(message_info) = serde_json::from_str::<MessageInfo>(&line_read.as_str())
                {   

                    let msg : MessageInfo = message_info.clone(); 
                    
                    msg_optional = Some(msg);
                }

            }
            
            let mut msg : MessageInfo;
            let mut address : String = String::new();
            if msg_optional.is_some()
            {   
                msg = msg_optional.unwrap();
                let receiverStr = msg.clone().receiver;
                
                let addressStr : String = msg.clone().addr;
                let senderStr : String = msg.clone().sender;
                
                let insert_res = insert_new_user_to_db(senderStr, addressStr);

                address = get_port_number_from_id(receiverStr).unwrap();
                if address.is_empty()
                {
                    return;
                }
                
                if(msg.clone().data.is_empty())
                {
                    return;
                }
                let forward_socket = std::net::TcpStream::connect(
                    address
                );         
                if let Ok(mut forward_socket) = forward_socket
                {
                    
                    let forward_msg = serde_json::to_string(&msg).expect("Can't transform message into JSON.");

                    if let Err(_) = forward_socket.write_all(forward_msg.as_bytes())
                    {
                        println!("Failed to send message to specified address");
                    }
                }
            

            line_read.clear();
            
            msg_optional = None;
            
            }
        });
    }
}