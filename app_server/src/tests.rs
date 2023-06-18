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
    // To be added.
}
