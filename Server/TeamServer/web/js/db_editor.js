/**
 * Создание пользователя в базе данных.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
function createUser() {
    var url = document.contextPath + "/editor";
    var data = "";

    data += "name=" + document.getElementById("name").value;
    data += "&lastname=" + document.getElementById("lastname").value;
    data += "&email=" + document.getElementById("email").value;
    data += "&password=" + document.getElementById("password").value;
    data += "&act=create_user";

    console.log(data);

    var xhr = new XMLHttpRequest();
    xhr.open('POST', url + "?" + data, true);
    xhr.send();
    xhr.onreadystatechange = function() {
        if (this.readyState != 4) return;
        if (this.status != 200) {
            console.log( 'ошибка: ' + (this.status ? this.statusText : 'запрос не удался') );
            return;
        }

        console.log(this.responseText);
        var object = JSON.parse(this.responseText);
        console.log(object);
        alert(object.err_message + "\n\nError code: " + object.err_code + "\n" + object.err_local);
    }
}

/**
 * UTF-8 енкодер.
 * @param s строка изначальная.
 * @returns {string} закодированная строка.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
function encode_utf8(s) {
    return unescape(encodeURIComponent(s));
}

/**
 * UTF-8 декодер.
 * @param s закодированная строка
 * @returns {string} исходная строка.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
function decode_utf8(s) {
    return decodeURIComponent(escape(s));
}