/**
 * 1) * get_table_lenght(); 
 * 2) * get_index_by_value(TableName,Col_name,Col_value) ;
 * 3) * read_by_index(TableName,Col_name,index);
 * 4) * read_by_value(TableName,Col_name,Col_value);
 * 5) * read_by_colmun(TableName,Col_name);
 * 6) * add_row(TableName,Col_names,Col_values);
 * 7) * update_row(TableName,Col_names,Col_values);
 * 8) * delete_row(TableName,Col_names,Col_values);
 */

/********************************************
 *          Variables and Objects           *
 ********************************************/

var net = require('net');
var net2 = require('net');
const { promises } = require('stream');
var client = new net2.Socket();
var recieved_data = "default";
var prev_recieved_data = "default";
var dataBaseConnection=false;
var table_lenght=0;
var index_by_value=0;
var read_by_idx="default";
var read_by_val=false;
let read_by_clmn=[];
let max_time_out=600;


/********************************************
 *             F U N C T I O N S            *
 ********************************************/
function recieve()
{
    if(recieved_data != prev_recieved_data)
    {
        prev_recieved_data=recieved_data;
        return recieved_data.toString();
            
    }
}

function init()
{
    let sockets = [];
    var server = net.createServer((socket) =>{

        socket.on("error", (err) =>
        console.log("init(): client disconnected ....... ")
        )
            socket.on('data',data=>{
            console.log("recieved: "+data.toString());
            recieved_data  = data.toString();

        })
    })    


    server.listen(8082,'127.0.0.1',function()
    {    
         console.log("init(): server is listening for port 8082.....")
    });
/**
 *
 *  sockets.push(sock);
        sock.on('data', function(data) 
        {
        console.log('DATA ' + sock.remoteAddress + ': ' + data);
    
    })
 */
    server.on('connection', function(sock) {
        console.log('init(): a new client connection...... ');
    });

/************************************************************************** */
    client.connect(8081, '127.0.0.1', function() {
        console.log(' Connected to server ........');
        if(client.write('hello from the connector....'))  
        {
            console.log('init(): msg sent from the connector ....');
        }    
        else
        {
            console.log('init(): msg failed to be sent..........');
        }  
    });
    
    client.on('close', function() {
        console.log('init(): Connection closed');
    });

}    

function Send(x)
{
   
   
    if(client.write(x))  
    {
        console.log('send(): msg sent');
    }    
    else
    {
        console.log('send(): msg failed to be sent..........');
    }               
    
     

}

function get_db_conn_status(table_name)
{
    var cmd=0x01;
    var request= '$' + '#' + cmd + '#'+'#'+table_name+'#' + '@';
    Send(request);

    let rec="default";
    setTimeout(() => { rec=recieve(); 
    const buffer= rec?.split('#');
    console.log("*********************************");
    console.log("from get_db_conn_status(table_name):");

   if(buffer[0]=='$' && buffer[buffer.length-1]=='@')
   {
    console.log("valid respond recieved ......");
    if(buffer[1]=="1")
    {
        
        console.log("passed from true");
        console.log("*********************************")
        dataBaseConnection= true;
    }
    else
    {
        console.log("passed from false");
        console.log("*********************************")
        dataBaseConnection= false;
    }

   }

    },500);

   
}
function get_table_lenght(table_name)
{
    var cmd=0x08;
    var request= '$' + '#' + cmd + '#!'+'#'+table_name+'#' + '@';
    Send(request);

    let rec="default";
    setTimeout(() => { rec=recieve(); 
    const buffer= rec?.split('#');
    console.log("*********************************");
    console.log("from get_table_lenght():");
   if(buffer[0]=='$' && buffer[buffer.length-1]=='@')
   {
    console.log("valid respond recieved ......");
    table_lenght = parseInt(buffer[2]);

   }
   console.log("*********************************");
   },500);

}

function get_index_by_value(TableName,Col_name,Col_value)
{
    var cmd=0x09;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#"+Col_name+"#~#"+Col_value+'#' + '@';
    Send(request);

    let rec="default";
    setTimeout(() => { rec=recieve(); 
    const buffer= rec?.split('#');
    console.log("*********************************");
    console.log("from get_index_by_value(...):");

   if(buffer[0]=='$' && buffer[buffer.length-1]=='@')
   {
    console.log("valid respond recieved ......");
    index_by_value = parseInt(buffer[2]);

   }
   console.log("*********************************");
   },500);

}
function read_by_index(TableName,Col_name,index)
{
    var cmd=0x05;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#"+Col_name+"#~#"+index.toString()+'#' + '@';
    Send(request);

    let rec="default";
    setTimeout(() => { rec=recieve(); 
    const buffer= rec?.split('#');
    console.log("*********************************");
    console.log("from read_by_index(...):");

   if(buffer[0]=='$' && buffer[buffer.length-1]=='@')
   {
    console.log("valid respond recieved ......");
    var lidx=0;
    for(let i=2;i<2000;i++)
    {
        if(buffer[i]=='@')
        {
            lidx=i;
            break;
        }

    }
    read_by_idx ="";
    for(let i=2;i<lidx;i++)
    {

        read_by_idx += buffer[i];

    }
   }
   console.log("*********************************");
   },500);

}

function read_by_value(TableName,Col_name,Col_value)
{
    var cmd=0x06;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#"+Col_name+"#~#"+Col_value+'#' + '@';
    Send(request);

    let rec="default";
    setTimeout(() => { rec=recieve(); 
    const buffer= rec?.split('#');
    console.log("*********************************");
    console.log("from read_by_value(...):");

   if(buffer[0]=='$' && buffer[buffer.length-1]=='@')
   {
    console.log("valid respond recieved ......");
    if(buffer[2]=='1')
    {
        read_by_val = true;
    }
    else
    {
        read_by_val = false;
    }

   }
   console.log("*********************************");
   },500);

}

function read_by_colmun(TableName,Col_name)
{
    var cmd=0x07;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#"+Col_name+'#' + '@';
    Send(request);

    let rec="default";
    let tmp="";
    setTimeout(() => { rec=recieve(); 
    const buffer= rec?.split('^#');
    console.log("*********************************");
    console.log("from read_by_colmun(...):");

    for(let i=1;i<buffer?.length-1;i++)
    {
        read_by_clmn.push(buffer[i]);
    }

   console.log("*********************************");
   },500);


}

function add_row(TableName,Col_names,Col_values)
{
    var cmd=0x04;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#";
    for(let i=0;i<Col_names.length;i++)
    {
        request += Col_names[i];
        request += '#';
    }
    request += "~#";
    for(let i=0;i<Col_values.length;i++)
    {
        request += Col_values[i];
        request += '#';
    }
    request += '@';
    Send(request);


}

function update_row(TableName,Col_names,Col_values)
{
    var cmd=0x02;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#";
    for(let i=0;i<Col_names.length;i++)
    {
        request += Col_names[i];
        request += '#';
    }
    request += "~#";
    for(let i=0;i<Col_values.length;i++)
    {
        request += Col_values[i];
        request += '#';
    }
    request += '@';
    Send(request);
}
function delete_row(TableName,Col_names,Col_values)
{
    var cmd=0x03;
    var request= '$' + '#' + cmd + '#!'+'#'+TableName+"#%#";
    for(let i=0;i<Col_names.length;i++)
    {
        request += Col_names[i];
        request += '#';
    }
    request += "~#";
    for(let i=0;i<Col_values.length;i++)
    {
        request += Col_values[i];
        request += '#';
    }
    request += '@';
    Send(request);
}



/********************************************
 *           Main Process Calls             *
 ********************************************/

init();

/************************************(tested) 
=> test for get_db_conn_status(...)
**************************************

get_db_conn_status("users");
setTimeout(() => {
console.log("x after is: "+dataBaseConnection)    
if(dataBaseConnection)
{
    console.log("connected to database successfully")
}
else
{
    console.log("failed to connect to database")

}
},max_time_out)
*/
 



/************************************ (tested)
=> test for get_table_lenght(...)
**************************************/

get_table_lenght("users");
setTimeout(() => {
console.log("table lenght is : "+table_lenght);    

},max_time_out);


 

/************************************ (tested)
=> test for get_index_by_value(...)
*************************************

get_index_by_value("users","name","ahmed");
setTimeout(() => {
console.log("index of value is : "+index_by_value);    
},max_time_out)
*/


/************************************ (tested)
=> test for read_by_index(...)
**************************************

read_by_index("users","name",5);
setTimeout(() => {
console.log("content at index : "+parseInt(read_by_idx));    
},max_time_out)
*/


/************************************ (tested)
=> test for read_by_colmun(...)
*************************************

read_by_colmun("users","name");
setTimeout(() => {
console.log("table colomun is : [ "+read_by_clmn+" ]");    
},max_time_out)
*/


/************************************ (tested)
=> test for read_by_value(...) 
*************************************

read_by_value("users","name","ahmed");
setTimeout(() => {
console.log("read by value is : "+read_by_val);    
},max_time_out)
*/


let tname="users";
let cnames= ["id","name","password","age","position","hospital"];
let cvalues= ["13","fadl","abcd","35","doctor","elmansoura emergency hospital"];

// test for add_row(...) (tested)
//add_row(tname,cnames,cvalues);
// test for update_row(...) (tested)
//update_row(tname,cnames,cvalues);
// test for delete_row(...) (tested) 
//delete_row(tname,cnames,cvalues);




/**
 *    if(buffer[0]=='$' && buffer[buffer.length-1]=='@')
   {
    console.log("valid respond recieved ......");
    
    for(let j=4;j<2000;j++)
    {
        if(buffer[j] != '@')
        {
            var lidx=0;
            for(let i=j;i<2000;i++)
            {
                if((buffer[i]=='^') || (buffer[i]=='@'))
                {
                    lidx=i;
                    break;
                }
        
            }
            
            for(let i=2;i<lidx;i++)
            {
                tmp += buffer[i];
                read_by_clmn.push(tmp);
        
            }
            j += lidx-1;
        }
    }
   }
 */

















/**
 *    for(let i=0;i<buffer?.length;i++)
   {
     console.log("buffer["+i.toString()+"] = "+buffer[i]);
     if(buffer[1]=="1")
     {
         console.log("true");
     }
   }  
    */
 








