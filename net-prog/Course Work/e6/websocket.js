const net = require('net');
const crypto = require('crypto');

const http = require('http');
const fs = require('fs');
const path = require('path');

// HTTP-server for å servere index.html
const httpServer = http.createServer((req, res) => {
    if (req.url === '/') {
        fs.readFile(path.join(__dirname, 'index.html'), (err, data) => {
            if (err) {
                res.writeHead(500);
                res.end('Error loading index.html');
            } else {
                res.writeHead(200, { 'Content-Type': 'text/html' });
                res.end(data);
            }
        });
    }
});

httpServer.listen(3000, () => {
    console.log('HTTP server listening on port 3000');
});


const clients = new Set()

const wsServer = net.createServer((socket) => {
    console.log('Client connected');
    clients.add(socket);

    socket.on('data', (data) => {
        if (!socket.isUpgraded) {
            handleHandshake(socket, data);
        } else {
            const message = decodeMessage(data);
            console.log('Received:', message);
            broadcast(message, socket);
        }
    });

    socket.on('end', () => {
        console.log('Client disconnected');
        clients.delete(socket);
    });

    socket.on('error', (err) => {
        console.error('Socket error:', err);
        clients.delete(socket);
    });
});

function handleHandshake(socket, data) {
    const request = data.toString();
    const match = request.match(/Sec-WebSocket-Key: (.+)\r\n/);
    if (!match) return socket.end();

    console.log("Request match key: " + match[1]);

    const acceptHash = generateAcceptHash(match[1]);
    const responseHeaders = [
        'HTTP/1.1 101 Switching Protocols',
        'Upgrade: websocket',
        'Connection: Upgrade',
        `Sec-WebSocket-Accept: ${acceptHash}`,
        '\r\n'
    ].join('\r\n');
    
    console.log("Generated accept key: " + acceptHash);


    socket.write(responseHeaders);
    socket.isUpgraded = true;
    console.log('Handshake complete');
}

function generateAcceptHash(key) {
    return crypto.createHash('sha1').update(key + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11').digest('base64');
}

function decodeMessage(buffer) {
    if (buffer.length < 2) return '';

    const secondByte = buffer[1];
    let length = secondByte & 127;
    let offset = 2;

    if (length === 126) {
        length = buffer.readUInt16BE(offset);
        offset += 2;
    } else if (length === 127) {
        length = Number(buffer.readBigUInt64BE(offset));
        offset += 8;
    }

    const mask = buffer.slice(offset, offset + 4);
    offset += 4;
    const payload = buffer.slice(offset, offset + length);

    // Bruk Buffer for dekoding av UTF-8-tegn
    const decoded = Buffer.alloc(length);
    for (let i = 0; i < length; i++) {
        decoded[i] = payload[i] ^ mask[i % 4];
    }
    
    return decoded.toString('utf8');
}

function encodeMessage(message) {
    const payload = Buffer.from(message, 'utf8'); // Viktig for ikke-engelske tegn
    const length = payload.length;
    let frame;

    if (length <= 125) {
        frame = Buffer.alloc(2 + length);
        frame[1] = length;
    } else if (length <= 65535) {
        frame = Buffer.alloc(4 + length);
        frame[1] = 126;
        frame.writeUInt16BE(length, 2);
    } else {
        frame = Buffer.alloc(10 + length);
        frame[1] = 127;
        frame.writeBigUInt64BE(BigInt(length), 2);
    }

    frame[0] = 0x81;
    payload.copy(frame, frame.length - length);
    return frame;
}


function broadcast(message, sender) {
    for (const client of clients) {
        if (client !== sender) {
            client.write(encodeMessage(message));
        }
    }
}

wsServer.listen(3001, () => {
    console.log('WebSocket server listening on port 3001');
});
