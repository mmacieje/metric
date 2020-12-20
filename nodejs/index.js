const express = require('express')
var crypto = require('crypto');
const app = express();
app.use(express.json());
const port = 9100;


app.get('/', (req, res) => {
  res.send('Hello World!')
});

app.post('/', (req, res) => {
    var signature = ""
    for (var i=0; i<req.body.data.length; ++i)
    {
        signature += req.body.data[i].signature;
    }

    hashed_signature = crypto.createHash('sha256').update(signature).digest('hex');
    const message = {
        metric:{
            "signature": hashed_signature,
            "number-of-items": req.body.data.length,
        }
    };
    return res.json(message);
  });

app.listen(port, () => {
  console.log(`Server listening on port ${port}!`)
});
