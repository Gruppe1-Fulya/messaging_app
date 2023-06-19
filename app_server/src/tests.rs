#[cfg(test)]
pub mod tests {
    use tokio_test::{assert_ok, assert_err};
    use crate::database::database::{clear_user_table, get_port_number_from_id, insert_new_user_to_db};
    use crate::main_server::main_server::init_main_server;


    // ------ Tests for Database Fuctions ------ \\
    #[tokio::test]
    async fn test_clear_user_table() {
        let _ = clear_user_table();
        assert_eq!(get_port_number_from_id("enaciodabasi@outlook.com".to_string()).unwrap(), "");
    }

    #[tokio::test]
    async fn test_get_port_number_from_id() {
        let _ = insert_new_user_to_db(&"demo_user@demo.com".to_string(), &"1234".to_string());
        assert_eq!(get_port_number_from_id(String::from("demo_user@demo.com")).unwrap(), String::from("1234"), "Test - Getting port number from id");
    }

    #[tokio::test]
    async fn test_insert_new_user_to_db() {
        let _ = insert_new_user_to_db(&"demo_user_2@demo.com".to_string(), &"5678".to_string());
        assert_eq!(get_port_number_from_id(String::from("demo_user_2@demo.com")).unwrap(), String::from("5678"), "Test - User insertion to the database");
    }
    
    
    // ------ Tests for Main Server ------ \\
    #[tokio::test] 
    async fn test_init_main_server() {

        let listener = TcpListener::bind("127.0.0.1:0").unwrap();

        let initial_active_connections = listener.local_addr().unwrap().port();

        let init_server_process = tokio::spawn(async move {
            init_main_server().await;
        });

        let client_socket = TcpStream::connect(listener.local_addr().unwrap()).unwrap();

        tokio::time::sleep(tokio::time::Duration::from_secs(1)).await;

        let final_active_connections = listener.local_addr().unwrap().port();

        init_server_process.abort();
        assert_eq!(initial_active_connections + 1, final_active_connections, "Test - Main server connection");
    }
}
