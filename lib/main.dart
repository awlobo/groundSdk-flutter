import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

void main() => runApp(const MyApp());

const CHANNEL = "com.awlobo.communication.channel";
const DRONE_STATUS = "droneStatus";

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

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

  static const platform = MethodChannel(CHANNEL);

  List<String> statusList = [];

  Future<dynamic> _handleMethod(MethodCall call) async {
    switch (call.method) {
      case DRONE_STATUS:
        debugPrint(call.arguments);
        _onTextChanged(call.arguments);
        return Future.value("");
    }
  }

  @override
  void initState() {
    super.initState();
    platform.setMethodCallHandler(_handleMethod);
  }

  void _onTextChanged(String droneStatus) {
    setState(() {
      statusList.add(droneStatus);
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
            Text(statusList.join("\n"))
          ],
        ),
      ),
    );
  }
}
