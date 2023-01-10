package bgu.spl.net.srv;

import java.io.IOException;

public interface Connections<T> //i changed to String, maybe need to change back to type T.
{
/*
 * 
 *  אמור להחזיק מיפוי בין קונקשיין איי די לקונקשיין הנדלר 
 להוסיף מחלקה של קונקשיין אימפל
 */

    boolean send(int connectionId, String msg);

    void send(String channel, String msg);

    void disconnect(int connectionId);
}
