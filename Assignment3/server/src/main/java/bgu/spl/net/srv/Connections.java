package bgu.spl.net.srv;

import java.io.IOException;

public interface Connections<T> 
{
 אמור להחזיק מיפוי בין קונקשיין איי די לקונקשיין הנדלר 
 להוסיף מחלקה של קונקשיין אימפל
    boolean send(int connectionId, T msg);

    void send(String channel, T msg);

    void disconnect(int connectionId);
}
