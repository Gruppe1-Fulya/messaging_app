use mysql::*;
use mysql::prelude::*;

#[derive(Debug, PartialEq, Eq)]
struct UserInfo
{
    id: i32,
    email : String,
    address: String,
}

pub fn insert_new_user_to_db(id : String, address : String) -> std::result::Result<(), Box<dyn std::error::Error>>
{

    let url  = "mysql://admin:123456@localhost:3306/mainserver_db";
    let pool = Pool::new(url)?;

    let mut conn = pool.get_conn()?;

    conn.exec_drop(
        r"INSERT INTO registered_users (email, address) VALUES (:email, :address)",
        params! {"email" => &id, "address" => &address}
    )?;


    Ok(())
}

pub fn get_port_number_from_id(email : String) -> std::result::Result<(), Box<dyn std::error::Error>>
{

    let url  = "mysql://admin:123456@localhost:3306/mainserver_db";
    let pool = Pool::new(url)?;

    let mut db_connection = pool.get_conn()?;

    let res : std::option::Option<String> = db_connection.exec_first(
        "SELECT address FROM registered_users WHERE email=:id",
        params! {
            "id" => email
        },
    )?;

    let address : String;
    if(res.is_some())
    {
        address = res.unwrap();
        println!("{:?}", address);
    }
    else {
        println!("No address found");
    }


    Ok(())
}