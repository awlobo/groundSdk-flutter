import 'package:flutter/material.dart';
import 'package:parrot_flutter/drone_status.dart';
import 'package:flutter/services.dart';

void main() => runApp(MyApp());

const CHANNEL = "id.awlobo.comm.channel";
const CONNECTION_KEY = "idDroneConnected";

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Parrot Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.green,
      ),
      home: const MyHomePage(title: 'Parrot-Flutter Demo'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  final String title;
  const MyHomePage({Key? key, required this.title}) : super(key: key);
  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {

  static const platform = const MethodChannel(CHANNEL);

  String _text = "Drone NOT connected";

  Future<Null> _isDroneConnect() async {
    await platform.invokeMethod(CONNECTION_KEY);
  }

  Future<dynamic> _handleMethod(MethodCall call) async {
    switch (call.method) {
      case "droneStatus":
        debugPrint(call.arguments);
        _onTextChanged(call.arguments);
        return new Future.value("");
    }
  }

  @override
  void initState() {
    super.initState();
    platform.setMethodCallHandler(_handleMethod);
    _isDroneConnect();
  }

  void _onTextChanged(Bool droneStatus) {
    setState(() {
      _text = droneStatus ? "Drone IS connected" : "Drone is NOT connected";
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(_text)
          ],
        ),
      ),
    );
  }
}
